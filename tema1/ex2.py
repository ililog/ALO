import sys
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

print(f"(x + y) + z = {ec_1}")
print(f"x + (y + z) = {ec_2}")

if ec_1 != ec_2:
    print("cele 2 ecuatii sunt inegale q.e.d")

x = sys.float_info.max #nr maxim pozitiv reprezentabil in float 
y = 2.0
z = sys.float_info.min #nr minim pozitiv reprezentabil in float 

print(f"x = {x}")
print(f"z = {z}")

ec_1 = (x * y) * z
ec_2 = x * (y * z)

print(ec_1)
print(ec_2)

if ec_1 != ec_2:
    print("cele 2 ecuatii sunt inegale q.e.d")