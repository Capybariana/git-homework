FROM jenkins/jenkins:lts-jdk17

USER root

# Установка зависимостей
RUN apt-get update && \
    apt-get install -y \
    curl \
    git \
    unzip \
    wget \
    sudo

# Установка Docker
RUN curl -fsSL https://get.docker.com | sh && \
    usermod -aG docker jenkins

# Установка kubectl
RUN curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl" && \
    install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl

# Установка Helm
RUN curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash

# Установка Terraform
RUN curl -LO https://releases.hashicorp.com/terraform/1.5.5/terraform_1.5.5_linux_amd64.zip && \
    unzip terraform_1.5.5_linux_amd64.zip && \
    mv terraform /usr/local/bin/ && \
    rm terraform_1.5.5_linux_amd64.zip

USER jenkins

# Установка плагинов Jenkins
RUN jenkins-plugin-cli --plugins \
    docker-workflow \
    kubernetes \
    pipeline-aws \
    terraform \
    git \
    github \
    blueocean