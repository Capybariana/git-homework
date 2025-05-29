pipeline {
    agent any

    environment {
        DOCKERHUB_CREDENTIALS = credentials('dockerhub-creds')
        GITHUB_TOKEN = credentials('github-token')
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Terraform Init & Apply') {
            steps {
                dir('terraform') {
                    sh 'terraform init'
                    sh 'terraform plan'
                    //sh 'terraform apply -auto-approve'
                }
            }
        }

        stage('Build & Push Docker Images') {
            steps {
                script {
                    // Сборка и пуш app
                    sh 'docker build -t app:latest -f Dockerfile.app .'
                    sh 'docker tag app:latest $DOCKERHUB_CREDENTIALS_USR/app:latest'
                    sh 'echo $DOCKERHUB_CREDENTIALS_PSW | docker login -u $DOCKERHUB_CREDENTIALS_USR --password-stdin'
                    sh 'docker push $DOCKERHUB_CREDENTIALS_USR/app:latest'
                    // Сборка и пуш web
                    sh 'docker build -t web:latest -f Dockerfile.web .'
                    sh 'docker tag web:latest $DOCKERHUB_CREDENTIALS_USR/web:latest'
                    sh 'docker push $DOCKERHUB_CREDENTIALS_USR/web:latest'
                }
            }
        }

        stage('Test C++ Application') {
            steps {
                sh 'g++ -o candle_test candle.cpp tests.cpp'
                sh './candle_test'
            }
        }

        stage('Package Helm Chart') {
            steps {
                dir('helm/test-repo-chart') {
                    sh 'helm package .'
                    sh 'helm repo index .'
                }
            }
        }

        stage('Publish to GitHub Pages') {
            steps {
                echo "Публикация Helm-чарта на GitHub Pages."
            }
        }

        stage('Deploy to Kubernetes') {
            steps {
                script {
                    def tgzFile = sh(script: "ls -t helm/test-repo-chart/*.tgz | head -n1", returnStdout: true).trim()
                    sh "helm upgrade --install testv3 ${tgzFile}"
                }
            }
        }
    }

    post {
        always {
            echo "Пайплайн завершён."
            sh 'docker logout'
        }
    }
}
