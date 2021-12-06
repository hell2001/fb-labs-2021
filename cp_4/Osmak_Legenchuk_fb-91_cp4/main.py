from prime import generate_prime

import math
import random


def generate_key_pair(p, q):
    n = p * q
    phi_n = (p - 1) * (q - 1)

    e = 0
    while math.gcd(e, phi_n) != 1:
        e = random.randrange(2, phi_n - 1)

    d = pow(e, -1, phi_n)

    return n, e, d


def encrypt(message, e, n):
    assert 0 <= message < n, "message value must be in interval"
    cryptogram = pow(message, e, n)
    return cryptogram


def decrypt(cryptogram, d, n):
    assert 0 <= cryptogram < n, "cryptogram value must be in interval"
    message = pow(cryptogram, d, n)
    return message


def sign(message, d, n):
    signed = pow(message, d, n)
    return signed


def verify(signed, message, e, n):
    return message == pow(signed, e, n)


def send_key(message, signed, n_recv, e_recv):
    return pow(message, e_recv, n_recv), pow(signed, e_recv, n_recv)


def receive_key(cryptogram, signed, n, d):
    return pow(cryptogram, d, n), pow(signed, d, n)


# Generate four prime numbers
primes = [generate_prime() for _ in range(4)]
primes.sort()
pA, qA, pB, qB = primes

print("Generate random number for two person")
print(f"pA = {pA}\nqA = {qA}\npB = {pB}\nqB = {qB}")
print(f"pA * qA <= pB * qB == {pA * qA <= pB * qB}")

print("A key pair")
nA, eA, dA = generate_key_pair(pA, qA)
print(f"n = {nA}\ne = {eA}\nd = {dA}")

print("B key pair")
nB, eB, dB = generate_key_pair(pA, qA)
print(f"n = {nB}\ne = {eB}\nd = {dB}")


###############################
message = 1234567890
print(f"<A> send message {message}")
cryptogram = encrypt(message, eA, nA)
print(f"<A> cryptogram {cryptogram}")
message = decrypt(cryptogram, dA, nA)
print(f"<A> decode cryptogram {message}")

signed = sign(message, dA, nA)
print(f"<A> sign message {message} {signed}")


print(f"<B> verify message {verify(signed, message, eA, nA)}")
#########################

print("Protocol")
# Message and sign of A
k = 1234567890
s = sign(message, dA, nA)

k1, s1 = send_key(k, s, nB, eB)
print(f"<A> generate  k1 = {k1}, s1 = {s1}")

k, s = receive_key(k1, s1, nB, dB)
print(f"<B> receive k = {k}, s = {s}")
print(f"<B> check sign {verify(s, k, eA, nA)}")
