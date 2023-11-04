# Commands

## Pulling images
docker pull mongo
docker pull mongo-express

## Create docker network
docker network create mongo-network

## Start mongodb
docker run -d \
-p 27017:27017 \
-e MONGO_INITDB_ROOT_USERNAME=admin \
-e MONGO_INITDB_ROOT_PASSWORD=password \
--net mongo-network \
--name mongodb \
mongo

## Start mongo-express
docker run -d \
-p 8081:8081 \
-e ME_CONFIG_MONGODB_ADMINUSERNAME=admin \
-e ME_CONFIG_MONGODB_ADMINPASSWORD=password \
-e ME_CONFIG_MONGODB_SERVER=mongodb \
--net mongo-network \
--name mongo-express \
mongo-express

docker run -d \
-p 3000:3000 \
--net dockercompose_default \
--name myapp \
myapp:latest
