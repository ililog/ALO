import sys
import numpy as np
import time
# --------partea 1------------
u = 1.0 # initital u = 10 ^ -0
m = 0
copie_u = u

while 1.0 + u != 1.0:
    copie_u = u
    u = u / 10
    m += 1

m = m-1 # in ultima iteratie u a devenit prea mic (0)

# --------partea 2------------

u = copie_u
x = 1.0
y = u / 10 
z = u / 10

ec_1 = (x + y) + z
ec_2 = x + (y + z)

print(f"x = {x}")
print(f"y = {y}")
print(f"z = {z}")

print(f"(x + y) + z = {ec_1}") # ceva mare adunat cu ceva la o putere mica ajunge sa ignore nr mic
print(f"x + (y + z) = {ec_2}") #2 * 10^-16 e destul de mare cat sa nu fie ignorat

if ec_1 != ec_2:
    print("cele 2 ecuatii sunt inegale q.e.d\n")

x = sys.float_info.max #nr maxim pozitiv reprezentabil in float 
y = 2.0
z = sys.float_info.min #nr minim pozitiv reprezentabil in float 

print(f"x = {x}")
print(f"y = {y}")
print(f"z = {z}")

ec_1 = (x * y) * z
ec_2 = x * (y * z)

print(f"(x*y)*z = {ec_1}")
print(f"x*(y*z) = {ec_2}")

if ec_1 != ec_2:
    print("cele 2 ecuatii sunt inegale q.e.d\n")

ok = 1
start_time = time.perf_counter()
while (ok) :
    N = 100000
    random_numbers = np.random.uniform(-N, N, size = 3)
    x = random_numbers[0]
    y = random_numbers[1]
    z = random_numbers[2]

    ec_1 = (x * y) * z
    ec_2 = x * (y * z)
    if ec_1 != ec_2:
        ok = 0
        print(f"x = {x}")
        print(f"y = {y}")
        print(f"z = {z}")
        print("cele 2 ecuatii sunt inegale q.e.d\n")
    
end_time = time.perf_counter()
print(f"Timp:{end_time-start_time}")

