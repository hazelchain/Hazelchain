import blocksmith

if __name__ == '__main__':
    kg = blocksmith.KeyGenerator()
    kg.seed_input('Truly random string. I rolled a dice and got 4.')
    key = kg.generate_key()
    print(key)
    address = blocksmith.BitcoinWallet.generate_address(key)
    print(address)
