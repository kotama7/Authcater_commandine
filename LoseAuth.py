import subprocess
import os

pardir = os.path.dirname(__file__)
if not os.path.exists(pardir+"\\password.exe"):
    if not os.path.exists(pardir+"\\get_mac.exe"):
        subprocess.run(["gcc","-o",f"{pardir}\\get_mac.exe",f"{pardir}\\get_mac.c","-liphlpapi","-lWS2_32"])
    mac = subprocess.run([pardir+"\\get_mac.exe"],capture_output=True).stdout.decode('utf-8')
    KEY = input("二段階認証の秘密鍵を入力してください>>>")
    subprocess.run(["gcc","-o",f"{pardir}\\password.exe",f"-DSECRET_KEY={KEY}",f'-DMAC_ADDRESS="{mac}"',f"{pardir}\\password.c","-liphlpapi","-lWS2_32"])
key = subprocess.run([pardir+"\\password.exe"],capture_output=True).stdout.decode("utf-8")[0:6]
print(key)