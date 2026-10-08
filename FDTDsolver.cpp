#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

// Расчет значения Гауссова импульса для шага времени t
double get_pulse(int t, double t0, double sigma) {
    return std::exp(-0.5 * std::pow((t - t0) / sigma, 2));
}

// Шаг обновления магнитного поля H
std::vector<double> update_H(std::vector<double> H, const std::vector<double>& E, double S) {
    for (size_t i = 0; i < H.size() - 1; ++i) H[i] += S * (E[i + 1] - E[i]);
    return H;
}

// Шаг обновления электрического поля E с учетом диэлектрика eps
std::vector<double> update_E(std::vector<double> E, const std::vector<double>& H, const std::vector<double>& eps, double S) {
    for (size_t i = 1; i < E.size() - 1; ++i) E[i] += (S / eps[i]) * (H[i] - H[i - 1]);
    return E;
}

int main() {
    // Константы расчетной сетки и параметров схемы
    const int SIZE = 400, MAX_TIME = 600, SOURCE_POS = 50, GRID_MID = 200;
    const double S = 1.0, eps_dielectric = 4.0, t0 = 40.0, sigma = 12.0;

    // Инициализация полей и профиля диэлектрической среды
    std::vector<double> E(SIZE, 0.0), H(SIZE, 0.0), eps(SIZE, 1.0);
    std::fill(eps.begin() + GRID_MID, eps.end(), eps_dielectric); // Правая часть — диэлектрик

    // Переменные для хранения состояния поглощающих границ Mur ABC
    double old_first = 0.0, old_last = 0.0;

    std::cout << "Запуск 1D FDTD солвера..." << '\n';

    for (int t = 0; t < MAX_TIME; ++t) {
        H = update_H(H, E, S);
        E[SOURCE_POS] += get_pulse(t, t0, sigma);
        E = update_E(E, H, eps, S);

        double next_first = E[1], next_last = E[SIZE - 2];
        E[0] = old_first; E[SIZE - 1] = old_last;
        old_first = next_first; old_last = next_last;

        // Сохранение расчетных слоев Ez для визуализации
        if (t == 120 || t == 220 || t == 380) {
            std::ofstream file("E_field_t_" + std::to_string(t) + ".txt");
            for (int i = 0; i < SIZE; ++i) file << i << " " << E[i] << "\n";
        }
    }

    return 0;
}
