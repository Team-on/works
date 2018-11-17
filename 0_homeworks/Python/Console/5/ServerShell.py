class Server:
    name="Name"
    ip="127.0.0.1"
    hddSize=100

    def TurnOn(self, newIp):
        self.ip = newIp
        print("New ip: ",  self.ip)
        print("Avaliable space: ",  self.hddSize)

    def TurnOff(self):
        ip = "127.0.0.1"

    def Calculations(self):
        if self.ip != "127.0.0.1":
            self.hddSize -= 1


class ServerShell:
    lastip = 2

    def __init__(self, servers):
        self.servers = servers

    def TurnOnAll(self):
        for s in self.servers:
            s.TurnOn("192.168.0." + str(self.lastip))
            self.lastip += 1

    def TurnOffAll(self):
        for s in self.servers:
            s.TurnOff()

    def CalculationsByIp(self, ip):
        for s in self.servers:
            if s.ip == ip:
                s.Calculations()

    def TurnOffServerByIp(self, ip):
        for s in self.servers:
            if s.ip == ip:
                s.TurnOff()

    def __add__(self, o):
        self.servers.append(o)


sh = ServerShell([Server(), Server(), Server(), Server(), ])

sh.TurnOnAll()