#!/usr/bin/python3.5

import json
from weibouser import WeiboUser
from weibocomment import WeiboComment

def extractComments(data):
    jsonData = json.loads(data)
    comments = []

    for data in jsonData["data"]:
        source = data["source"]
        text = data["text"]
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
    file = open("weibo_comment_data")
    for line in file.readlines():
        comments = extractComments(line)
        for comment in comments:
            comment.toString()
            break
        break

