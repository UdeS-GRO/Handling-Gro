from Comm.ControlMessage import *

class MessageIO:
    def __init__(self):
        self.devices = []

    def addDevice(self, dev):
        self.devices.append(dev)
    def getNbrDevices(self):
        return len(self.devices)

    def sendMessage(self,deviceIndex,msg):
        j = {}
        j["type"] = msg.getType()
        j["PLS"] = msg.getPayloadSize()
        j["data"] = msg.getPayload()

        self.devices[deviceIndex].sendJSon(j)

    def readMessage(self,deviceIndex):
        dev = self.devices[deviceIndex]

        if dev.isMessageAvailable():
            try:
                jSonMessage = dev.readJSon()
                msgType = jSonMessage["type"]
                if "data" in jSonMessage:
                    msgpayload = jSonMessage["data"]
                else:
                    msgpayload = []

                return ControlMessage(msgType, msgpayload)
            except:
                return None
        else:
            return None

