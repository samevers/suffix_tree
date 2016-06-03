#!/usr/bin/env python
# coding:utf-8
# 选取top what词
import sys

class Node:
    def __init__(self, str='', count=1):
        self.str = str
        self.count = count
        self.keys = []
        self.values = []

def scan_vec(node, v):
    v1 = v
    if(v1):
        if v1[0] in node.keys:
            node.count += 1
            scan_vec(node.values[node.keys.index(v1[0])], v1[1:])
        else:
            node.keys.append(v1[0])
            node.values.append( Node(v1[0]+node.str) )
            scan_vec(node.values[-1], v1[1:])

def print_node(node):
    for i in xrange(len(node.keys)):
        print('%s %d' % (node.keys[i], node.values[i].count))

def top_nodes(node, limit):
    vec=[]
    for i in xrange(len(node.keys)):
        vec.append( (node.keys[i],node.values[i].count) )
    vec = sorted(vec, key = lambda k:k[1], reverse = True)
    for i in xrange(len(vec)):
        key = vec[i][0]
        count = vec[i][1]
        if count > limit:
            print('%s : %d' % (key+node.str,count))
            top_nodes(node.values[node.keys.index(key)], limit)

if(len(sys.argv) > 1):
    lines=open(sys.argv[1], 'r').readlines()
else:
    lines=sys.stdin.readlines()
line_num = 0
root = Node()
for line in lines:
    line_num += 1
    # 去掉末尾回车
    #print(line[:-1])
    v = line.split('\t')
    if v and v[-1] == '\n':
        v = v[:-1]
    if v and v[-1] == '':
        v = v[:-1]
    v.reverse()
    #print(v)
    #print(v[0])
    scan_vec(root, v)

top_nodes(root, 200)
#print_node(root)
