#! /usr/bin/python3

import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
import json
from weibouser import WeiboUser
from weibocomment import WeiboComment

# 去掉评论中的html信息
def format_comment(line):
    line = line.strip()
    i = 0
    while i < len(line):
        if line[i] == '<':
            begin = i
            while i < len(line) and line[i] != ' ':
                i += 1
            if i < len(line):
                close_tag = '/' + line[begin+1:i] + '>'
                close_index = line.find(close_tag)
                if close_index != -1:
                    close_index_right = close_index + len(close_tag)
                    if close_index_right >= len(line):
                        line = line[:begin]
                        break
                    else:
                        line = line[:begin] + line[close_index_right:]
                        i = begin - 1
        i += 1
    return line

def extractComments(data):
    jsonData = json.loads(data)
    comments = []

    for data in jsonData["data"]:
        source = data["source"]
        text = format_comment(data["text"])
        cid = data["id"]

        uid = data["user"]["id"]
        name = data["user"]["screen_name"]
        profileUrl = data["user"]["profile_url"]
        profileImageUrl = data["user"]["profile_image_url"]
        verified = data["user"]["verified"]

        user = WeiboUser(uid, name, verified, profileUrl, profileImageUrl)

        comment = WeiboComment(cid, source, user, text)
        comments.append(comment)

    return comments


if __name__ == '__main__':
    for line in sys.stdin:
        comments = extractComments(line)
        for comment in comments:
            #comment.toString()
            print(comment.text)
