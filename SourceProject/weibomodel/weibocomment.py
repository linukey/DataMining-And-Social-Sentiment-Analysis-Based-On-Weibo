#!/usr/bin/python3.5

from weibouser import WeiboUser

class WeiboComment:
    def __init__(self, cid=None, source=None, user=None, text=None):
        self.cid = cid
        self.source = source
        self.user = user
        self.text = text


    def toJson(self):
        juser = {}
        jcomment = {}
        juser.update(self.user.__dict__)
        jcomment.update(self.__dict__)
        jcomment["user"] = juser
        return jcomment

    
    def fromJson(self, data):
        self.cid = data["cid"]
        self.source = data["source"]
        self.text = data["text"]

        user=WeiboUser()
        user.fromJson(data["user"])
        self.user = user


    def toString(self):
        print("cid:" + str(self.cid))
        print("source:" + self.source)
        print("text:" + self.text)
        print("user:")
        self.user.toString()


if __name__ == '__main__':
    info = \
    "{ \
        \"cid\":\"123\", \
        \"source\":\"xiaomi\", \
        \"text\":\"hello\", \
        \"user\": \
        { \
            \"uid\":\"456\", \
            \"name\":\"linukey\", \
            \"verified\":\"false\", \
            \"profileUrl\":\"haha\", \
            \"profileImageUrl\":\"xixi\" \
        } \
    }"
    
    import json

    jsonData = json.loads(info)
    comment = WeiboComment()
    comment.fromJson(jsonData)
    comment.toString()
