#include <iostream>
#include <cmath>
#include <windows.h>

void draw(double position)
{
    int screen_pos = static_cast<int>(std::round(position));

    for (int i = -20; i < screen_pos; ++i)
        std::cout << "-";

    std::cout << " []\n";
}

int main()
{
    double mass_;
    std::cout << "Enter Mass (kg): ";
    std::cin >> mass_;

    double spring_constant_;
    std::cout << "Enter Spring Constant (N/m): ";
    std::cin >> spring_constant_;

    double displacement_;
    std::cout << "Enter Initial Displacement (m): ";
    std::cin >> displacement_;

    double position_ = displacement_;
    double velocity_ = 0.0;
    double acceleration_ = 0.0;

    double time_ = 0.0;
    double dt_ = 0.05;

    constexpr double coeff_friction_ = 0.3;
    constexpr double epsilon = 1e-5;

    while (time_ <= 20.0)
    {
        double spring_acc = -spring_constant_ * position_ / mass_;

        int sign_vel = (velocity_ > 0) - (velocity_ < 0);
        double friction_acc = -coeff_friction_ * 9.81 * sign_vel;

        double total_acc = spring_acc + friction_acc;

        // Stop motion when velocity is tiny and friction can hold the block
        if (std::abs(velocity_) < epsilon && std::abs(total_acc) < coeff_friction_ * 9.81)
        {
            velocity_ = 0.0;
            acceleration_ = 0.0;
            draw(position_);
            break;
        }

        acceleration_ = total_acc;
        velocity_ += acceleration_ * dt_;
        position_ += velocity_ * dt_;

        draw(position_);

        Sleep(75); // milliseconds
        time_ += dt_;
    }

    std::cout << "Simulation stopped. Final position: " << position_ << "\n";
    return 0;
}
