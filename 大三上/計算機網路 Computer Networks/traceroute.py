from scapy.all import *
from time import time
from socket import gethostbyname, gethostbyaddr

destination = gethostbyname("cycu.edu.tw")
max_hops = 30
settingRTTtime = 1

for ttl in range(1, max_hops + 1):
    packet = IP(dst=destination, ttl=ttl) / ICMP()

    timings = []
    for i in range(settingRTTtime):
        t = time()
        reply = sr1(packet, verbose=0, timeout=1)
        if reply is None:
            timings.append("timeout")
        elif reply.haslayer(IP):
            timings.append(f"{(time() - t) * 1000:.2f}ms")

    try:
        hostname = gethostbyaddr(reply.src)[0]
    except:
        hostname = "Unknown"

    print(f"{ttl:2}. IP: {reply.src:15} RTT:{' '.join(timings):10} hostname:({hostname})")
    if reply.src == destination:
        break

