### （项目还在开发阶段，以下流程仅供参考）

### 项目构建流程
#### 第一步 : 打包proxy代码并构建proxy镜像
```
# 复制proxy源代码到proxy/proxy.tgz
cd ./proxy
docker build -t proxy .
```

#### 第二步 : 打包爬虫代码
```
# 复制spider源代码到spider/spider.tgz
```

#### 第三步 : 利用 docker-compose 构建整个项目
```
docker-compose up -d
```

#### 第四步 : 启动 proxy容器中的webserver
```
docker container exec proxy sh /start-server.sh
```

#### 第五步 : 进入 redis-cli
```
docker container exec -it redis redis-cli
```

#### 第六步 : 启动爬虫节点
```
...
```


### 注意
```
爬虫节点的扩充需要手动在docker-compose.yml里面进行修改
```
