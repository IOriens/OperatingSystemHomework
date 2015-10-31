n/bash
#Oriens
#09132015

sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
echo oracle-java8-installer shared/accepted-oracle-license-v1-1 select true | sudo /usr/bin/debconf-set-selections
sudo apt-get install Oracle-java8-installer
sudo apt-get install oracle-java8-set-default
java -version
