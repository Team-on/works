#incapsulation test

class Server:
    def __init__(self):
        self.__protected = "Protected"
        self.protected = "Not really protected"

    def TransferData(self):
        print("Transfer")

    def TransferData(self, data):
        print("Transfer:", data)

    def ControlledSelfDestruct(self, key):
        if key == 1:
            self.__SelfDestruct()
        else:
            print("Not enaugh rights")

    def __SelfDestruct(self):
        print("Destruct")

Server = Server()
Server.TransferData()
Server.TransferData(112512512)
#Server.SelfDestruct()
Server.ControlledSelfDestruct(1)

print(Server.protected)
#print(Server.__protected)