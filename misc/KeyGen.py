import base64
import random
import ecdsa


def random_string(length):
    lut = '1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    out = ''
    for i in range(length):
        out += random.choice(lut)
    return out


sk = ecdsa.SigningKey.generate(curve=ecdsa.SECP256k1)
private_key = sk.to_string().hex()
vk = sk.get_verifying_key()
public_key = vk.to_string().hex()
public_key = base64.b64encode(bytes.fromhex(public_key))

print('pr: ', private_key, '\npu: ', public_key)
print(base64.b64decode(public_key))

# Hi, hello there, How are you today? are you good? that's really nice
