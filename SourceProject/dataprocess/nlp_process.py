#! /usr/bin/python3

from snownlp import SnowNLP

if __name__ == '__main__':
    data = open('result')
    for line in data:
        snow = SnowNLP(line)
        print(line)
        print(snow.words)
        print(snow.sentiments)
