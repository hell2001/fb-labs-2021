import random


def miller_rabin(number, rounds):
    # https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
    d = number - 1
    r = 0

    while d & 1 == 0:
        r += 1
        d //= 2

    for _ in range(rounds):
        a = random.randrange(2, number - 1)
        x = pow(a, d, number)
        if x != 1 and x != number - 1:
            j = 1
            while j < r and x != number - 1:
                x = pow(x, 2, number)
                if x == 1:
                    return False
                j += 1
            if x != number - 1:
                return False

    return True


def is_prime(number, rounds=128):
    if number == 2 or number == 3:
        return True

    # Take very long time
    # for divisor in range(2, int(number ** 0.5) + 1):
    #     if number % divisor == 0:
    #         return False

    if number % 2 == 0:
        return False

    return miller_rabin(number, rounds)


def generate_prime_candidate(length=256):
    candidate = random.getrandbits(length)
    candidate |= (1 << length - 1) | 1  # Set first and last bit of number to one
    return candidate


def generate_prime(length=256):
    candidate = 4  # First non-prime number
    while not is_prime(candidate):
        print(f'Candidate {candidate}')
        candidate = generate_prime_candidate(length)

    print(f'Prime     {candidate}')
    return candidate
