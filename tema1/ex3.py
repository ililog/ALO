import math
import random
import time 
import numpy as np

c1 = 1/3
c2 = 2/15
c3 = 17/315
c4 = 62/2835

#P(x) = x + x^3 * (c1 + x^2 * (c2 + x^2 * (c3 + x^2 * c4)))
def my_tan(x):        
    x2 = x * x
    p = c4
    p = p * x2 + c3
    p = p * x2 + c2
    p = p * x2 + c1

    return x + x * x2 * p

def prelucrare(x):

    x = x % math.pi #tg(x) = tg(x + k*pi), daca x nu e de forma (pi/2) * (2k+1)

    #il aduc in intervalul [-pi/2, pi/2]
    if x > math.pi/2:
        x = x - math.pi

    #tg(pi/2) = +inf , tg(-pi/2) = -inf
    if math.isclose(abs(x), math.pi / 2, rel_tol=1e-15): #|x-pi/2| <= epsilon * max(|a|,|b|) (eroare de 0,000..01%)
        if x > 0: return float('inf')
        return -1.0 * float('inf')

    if x > math.pi/4:
        return 1.0 / my_tan(math.pi/2 - x) #pi/4 < x < pi/2: tg(x) = 1 / tg(pi/2 - x)
    if x < -math.pi/4:
        return -1.0 / my_tan(math.pi/2 + x) # tg(-x) = -tg(x)
    return my_tan(x)
    #pot apela my_tan si cu valori negative, nu trebuie sa ma complic cu semnul
    #my_tan(x) = x + c1 * x^3 + c2 * x^5 + c3 * x^7 + c4 * x^9
    #my_tan(-x) = -x + c1 * (-x)^3 + c2 * (-x)^5 + c3 * (-x)^7 + c4 * (-x)^9
    #my_tan(-x) = (-1) * (x + c1 * x^3 + c2 * x^5 + c3 * x^7 + c4 * x^9) = -my_tan(x)

N = 100000
random_numbers = np.random.uniform(-N, N, size = N)
suma_erori = 0

for x in random_numbers:
    suma_erori = suma_erori + abs(prelucrare(x) - math.tan(x))

start_timp_my = time.perf_counter()
for x in random_numbers:
    _ = prelucrare(x)
sfarsit_timp_my = time.perf_counter()

start_timp_library = time.perf_counter()
for x in random_numbers:
    _ = math.tan(x)
sfarsit_timp_library = time.perf_counter()

t1 = sfarsit_timp_my - start_timp_my
t2 = sfarsit_timp_library - start_timp_library
diff_timp = abs(t1-t2)

print(f"Suma erorilor absolute pentru {N} valori: {suma_erori:.10f}")
print(f"Timpul de executie al metodei polinomiale: {t1:.6f} secunde")
print(f"Timpul de executie al folosind biblioteca: {t2:.6f} secunde")
print(f"Diferenta de timp:{diff_timp:.6f}")