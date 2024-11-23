//
// Created by mohan on 23/11/2024.
//

#include "Option.h"

std::vector<double> EuropeanOption::get_expected_payoff(int number_of_simulations) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> dist(0, 1);

    std::vector<double> payoffs(number_of_simulations);

    for (int i = 0; i < number_of_simulations; i++) {
        double option_price = initial_price * std::exp((risk_free_rate - 0.5 * std::pow(volatility, 2)) *
                              time_to_maturity
                              + volatility * std::sqrt(time_to_maturity) * dist(rng)
        );
        ;
        double payoff_arg = std::pow(-1, is_put_option) * (option_price - strike_price);
        double payoff = std::max(payoff_arg, 0.0);
        double discounted_payoff = std::exp(-risk_free_rate * time_to_maturity) * payoff;
        payoffs[i] = discounted_payoff;
    }

    double average_payoff = std::accumulate(payoffs.begin(), payoffs.end(), 0.0) / number_of_simulations;
    double sq_sum_payoffs = std::inner_product(payoffs.begin(), payoffs.end(), payoffs.begin(), 0.0);
    double stddev_payoffs = std::sqrt(((sq_sum_payoffs / number_of_simulations) - std::pow(average_payoff, 2)));

    double confidence_interval = 1.96 * stddev_payoffs / std::sqrt(number_of_simulations);
    double confidence_lower_bound = average_payoff - confidence_interval;
    double confidence_upper_bound = average_payoff + confidence_interval;

    return std::vector<double>{confidence_lower_bound, average_payoff, confidence_upper_bound};
}

std::vector<double> EuropeanOption::get_option_price(std::vector<double> expected_payoffs) {
    std::vector<double> option_prices(expected_payoffs.size());

    for (int i = 0; i < expected_payoffs.size(); i++) {
        option_prices[i] = std::exp(-risk_free_rate * time_to_maturity) * expected_payoffs[i];
    }

    return option_prices;
}


EuropeanCallOption::EuropeanCallOption(double current_price_input, double risk_free_rate_input, double volatility_input,
                                       double time_to_maturity_input,
                                       double strike_price_input) {
    initial_price = current_price_input;
    risk_free_rate = risk_free_rate_input;
    volatility = volatility_input;
    time_to_maturity = time_to_maturity_input;
    strike_price = strike_price_input;
}

EuropeanPutOption::EuropeanPutOption(double current_price_input, double risk_free_rate_input, double volatility_input,
                                     double time_to_maturity_input,
                                     double strike_price_input) {
    initial_price = current_price_input;
    risk_free_rate = risk_free_rate_input;
    volatility = volatility_input;
    time_to_maturity = time_to_maturity_input;
    strike_price = strike_price_input;
}
