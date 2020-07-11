#ifndef SJD_BLACKS76_INCLUDED
#define SJD_BLACKS76_INCLUDED

#include <math.h>
#include <boost/math/distributions/normal.hpp> // for normal_distribution

namespace sjd {

   /*======================================================================================
    NOTE: At this level we ONLY price options and provide one default method for valuing the
    option after maturity. We leave complex expiry business logic to the contract which has
    much more information. Note
            1) we implement options with unitless inputs (discount factors (df) instead of 
               interest rates; standard deviations (sd) instead of vols etc) and need to offer
               some type of sensible sanity testing for these inputs (sd > 0, df > 0 etc). 
               Once past maturity or settlement we would not be able implement these.
            2) To keep the code as clean and efficient as possible (I only want to check
               if the option is a put or a call once, I only want to check if the option
               is has matured but not settled one etc)
    =======================================================================================*/


   /*======================================================================================
    Black76Option: Black '76 Futures Option pricing algorithm.

    This simple model contains no greeks (analytic or numberic) because in almost every 
    contract there will be a specific way to calculate these measures. These specific bumps
    require additional date, calendar and curve information. Greeks used in a trading system are
    always numeric and should always use the contract's logic. It is therefore left to the
    contract to make repeated calls to this formula or the Portfolio to make repeated calls
    of the contract to calculate greeks because only at those levels will we have sufficient 
    information to to bump inputs.
        
    Wherever possible, inputs to this formula are unitless so. In particular
    the formula makes use of
      - discount factors rather than interest rates; 
      - standard deviation rather than volatility; and 
    This is done to achieve the safest implementation so there can be no doubt about 
    conventions or units. It is also the optimal implemenation in terms of speed which
    will become an issue when performing Monte Carlo simulations
        
    Calls and puts are implemented in separate objects to prevent the constant checking
        if (PutCallFlag == PUT) {...} 
    at all the time and at all levels. The responsibility of calling the correct (P)ut or 
    (C)all option is deferred to the Contract
    
    Wherever necessary, the following shorthand is used
        - OP: option premium
        - F: forward
        - X: strike
        - sd: standard deviation
        - df: discount factor

    You will note there are no time variables in this formula. The reason for this is that
    in practice "time" should have calendar and date logic which should be embedded in the 
    interest rate, forward and volatility rate source. These could all be slightly different
    and it would be very difficult to ensure consistency between "dumb" formula and clever
    rate sources without embedding a lot of logic which is 
        - unnecessary
        - only going to make the code more error prone and slower

    @author Steve Davey
    @version 1.0 03/99
    =======================================================================================*/
    class Black76Option
    {

    public :
  
       void setParameters(double forward, double strike, double standardDeviation, double discountFactor);

        //It is recommended, but optional, to call this method after setting any parameters.
        //If this method is not called, no error checking will happen so it is up to the 
        //user to either check the parameters are ok before trying to use the methods in this 
        // class or to call this isOK() method.
        //This method will return false if any of the input variables are negative
        virtual bool isOK();
        //The error message will only be populated if the isOK() method is called and
        //there is a problem with one or more of the inputs. Only the first error
        //will be displayed in this message.
        std::string getErrorMessage()           {return errorMessage;};
        
        double getForward()                     {return F;};
        void setForward(double forwardInput);
        double getStrike()                      {return X;};
        void setStrike(double strikeInput);
        double getStandardDeviation()           {return sd;};
        void setStandardDeviation(double sd); 
        double getDiscountFactor()              {return df;};
        void setDiscountFactor(double df);

        // present value
        virtual double value() = 0;
        // After maturity but before settlement
        virtual double payoff(double rateSetRate) = 0;        
        // I have had to include this for use in the delta surface rather than for 
        // use in an option
        virtual double delta() = 0; 
    protected :

        // This resets all internal variables when an option paramter is set / reset
        void callWhenSettingAnyInternalParameter();

        //When changing any of the input parameters we need to recalculate d1, d2, Nd1, Nd2
        void calculateInternalOptionParameters();
   
        double F, sd, df, X;
        // boost N(0,1)
        boost::math::normal n_0_1;
        double d1, d2, Nd1, Nd2;
        std::string errorMessage;

    };

    /*======================================================================================
    Black76Call: The call option
    =======================================================================================*/
    class Black76Call : public Black76Option
    {
    public :
        Black76Call(double forward, double strike, double standardDeviation, double discountFactor);
        bool isOK();
        double value();
        double payoff(double rateSetRate) {return std::max(rateSetRate - X, 0.0);};
        double delta(); 

    };

   /*======================================================================================
    EuropeanPutBlack76
    =======================================================================================*/
    class Black76Put : public Black76Option
    {
    public :
        Black76Put(double forward, double strike, double standardDeviation, double discountFactor);
        bool isOK();
        double value();
        double payoff(double rateSetRate) {return std::max(X - rateSetRate, 0.0);};
        double delta(); 
    };

}

#endif