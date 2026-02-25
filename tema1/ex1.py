u = 1.0 # initital u = 10 ^ -0
m = 0
copie_u = u

while 1.0 + u != 1.0:
    copie_u = u
    u = u / 10
    m += 1

m = m-1 # in ultima iteratie u a devenit prea mic (0)

print(f"u (precizia masina) este egal cu {copie_u:.20f} iar puterea m = {m}\n")