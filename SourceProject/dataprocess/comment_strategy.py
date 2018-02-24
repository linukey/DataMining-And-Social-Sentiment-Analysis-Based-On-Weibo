import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
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
    for line in sys.stdin:
        comments = extractComments(line.split('\t')[1])
        for comment in comments:
            comment.toString()
            break
