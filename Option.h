//
// Created by mohan on 23/11/2024.
//
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <cmath>

#ifndef OPTION_H
#define OPTION_H


class Option {
protected:
    double initial_price = 0;
    double risk_free_rate = 0;
    double volatility = 0;
    double time_to_maturity = 0;
    double strike_price = 0;
    // This is used when calculating the expected payoff
    int is_put_option = 0;

public:
    // No constructor for base class as we don't want the user to create this base class
    double get_initial_price() const { return initial_price; }
    double get_risk_free_rate() const { return risk_free_rate; }
    double get_volatility() const { return volatility; }
    double get_time_to_maturity() const { return time_to_maturity; }
    double get_strike_price() const { return strike_price; }

    virtual ~Option();

    virtual std::vector<double> get_expected_payoff(int) = 0;

    virtual std::vector<double> get_option_price(std::vector<double>) = 0;
};

class EuropeanOption : public Option {
public:
    ~EuropeanOption() override = default;

    std::vector<double> get_expected_payoff(int) override;

    std::vector<double> get_option_price(std::vector<double>) override;
};

class EuropeanCallOption : public EuropeanOption {
private:
    int is_put_option = 0;

public:
    EuropeanCallOption(double initial_price, double risk_free_rate, double volatility, double time_to_maturity,
                       double strike_price);

    ~EuropeanCallOption();
};

class EuropeanPutOption : public EuropeanOption {
private:
    int is_put_option = 1;

public:
    EuropeanPutOption(double initial_price, double risk_free_rate, double volatility, double time_to_maturity,
                      double strike_price);

    ~EuropeanPutOption();
};


#endif //OPTION_H
