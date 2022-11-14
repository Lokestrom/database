import struct

class writeFile:
    splitByte = (178).to_bytes(1, byteorder='big', signed=False)
    def __init__(self, file):
        self.file = open(file, "wb")

    def __del__(self):
        if(self.file.closed):
            self.file.write("\0")
            self.file.close()

    def open(self, file):
        if(not self.file.closed):
            raise Exception("File was not closed before opening new one")
        self.file = open(file, "wb")

    def close(self):
        if(self.file.closed):
            self.file.write("\0")
            self.file.close()

    def addColumns(self, columns):
        self.file.write((len(columns)).to_bytes(4, byteorder='big', signed=False))
        for i in columns:
            bytes = bytearray(i, "utf-8")
            self.file.write(bytes)
            self.file.write(self.splitByte)
    
    def addDataFloat(self, data):
        for i in data:
            self.file.write(bytearray(struct.pack("f", i)))