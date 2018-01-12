# Python Blockchain
# Sammy Hasan
# 2018
# following https://www.youtube.com/watch?v=p4lw8CuQtq8

import hashlib
import datetime

class Block:
    def __init__(self,prev_block_hash,data,timestamp):
        self.prev_block_hash = prev_block_hash
        self.data = data
        self.timestamp = timestamp
        self.hash = self.get_hash()

    @staticmethod
    def create_genesis_block():
        return Block('0','0',datetime.datetime.now())
    def get_hash(self):
        header_bin = (str(self.prev_block_hash)+str(self.data)+str(self.timestamp)).encode()
        inner_hash = hashlib.sha256(header_bin).hexdigest().encode()
        outer_hash = hashlib.sha256(inner_hash).hexdigest()
        return outer_hash


# b1 = Block.create_genesis_block()
# print(b1.hash)

block_chain = [Block.create_genesis_block()]
print('Genesis Block has been created')
print('Hash is %s' % block_chain[-1].hash)

num_blocks_to_add = 10

for i in range(1,num_blocks_to_add+1):
    block_chain.append(Block(block_chain[-1].hash,'DATA',datetime.datetime.now()))

    print('Block #%d has been created' % i)
    print('Block #%d hash: %s' %(i,block_chain[i].hash))
