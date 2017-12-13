class WeiboUser:
    def __init__(self, uid=None, name=None, verified=None, profileUrl=None, profileImageUrl=None):
        self.name = name
        self.uid = uid
        self.verified = verified
        self.profileUrl = profileUrl
        self.profileImageUrl = profileImageUrl

    
    def toJson(self):
        juser = {}
        juser.update(self.__dict__)
        return juser


    def fromJson(self, data):
        self.name = data["name"]
        self.uid = data["uid"]
        self.verified = data["verified"]
        self.profileUrl = data["profileUrl"]
        self.profileImageUrl = data["profileImageUrl"]


    def toString(self):
        print("uid:" + str(self.uid))
        print("name:" + self.name)
        print("verified:" + str(self.verified))
        print("prifileUrl:" + self.profileUrl)
        print("profileImageUrl:" + self.profileImageUrl)
