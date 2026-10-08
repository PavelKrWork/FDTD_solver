import matplotlib.pyplot as plt
import numpy as np

try:
    d120 = np.loadtxt('E_field_t_120.txt')
    d220 = np.loadtxt('E_field_t_220.txt')
    d380 = np.loadtxt('E_field_t_380.txt')
except IOError:
    print("Ошибка: Сначала скомпилируйте и запустите C++ бинарник!")
    exit()

x = d120[:, 0]

plt.figure(figsize=(10, 5.5))
plt.plot(x, d120[:, 1], label='t = 120 (Свободное распространение в вакууме)', color='blue', linewidth=1.5)
plt.plot(x, d220[:, 1], label='t = 220 (Нормальное падение на границу)', color='orange', linewidth=1.5)
plt.plot(x, d380[:, 1], label='t = 380 (Суперпозиция отраженной и прошедшей волн)', color='green', linewidth=1.5)

# Визуальное выделение диэлектрической среды
plt.axvline(x=200, color='red', linestyle='--', alpha=0.8, label='Интерфейс вакуум/диэлектрик (X = 200)')
plt.axvspan(200, 400, color='gray', alpha=0.1, label='Диэлектрик (eps = 4.0, mu = 1.0)')

plt.title('1D FDTD Direct Time Integration: Распределение электрического поля Ez', fontsize=11, fontweight='bold')
plt.xlabel('Пространственная координата сетки (дискретные ячейки)', fontsize=10)
plt.ylabel('Напряженность электрического поля Ez (отн. ед.)', fontsize=10)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(loc='upper right', fontsize=9)
plt.xlim(0, 400)

plt.savefig('fdtd_1d_result.png', dpi=300, bbox_inches='tight')
print("График успешно сохранен как файл 'fdtd_1d_result.png'!")
plt.show()
