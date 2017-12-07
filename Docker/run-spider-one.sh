#/bin/bash
docker container run -it --link webserver:webserver --link redis:rs --name spider-one weibo
