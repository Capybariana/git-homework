pipeline {
    agent any

    environment {
        DOCKERHUB_CREDENTIALS = credentials('dockerhub-creds')  // Настроить в Jenkins
        GITHUB_TOKEN = credentials('github-token')              // GitHub Personal Access Token
        REPO_URL = 'https://github.com/Capybariana/git-homework'
        BRANCH = 'feature/k8s-helm'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: "refs/heads/${BRANCH}"]],
                    userRemoteConfigs: [[url: REPO_URL]]
                ])
            }
        }

        stage('Docker Login') {
            steps {
                sh 'echo $DOCKERHUB_CREDENTIALS_PSW | docker login -u $DOCKERHUB_CREDENTIALS_USR --password-stdin'
            }
        }

        stage('Setup Buildx') {
            steps {
                sh 'docker buildx create --use'
            }
        }

        stage('Build App Image') {
            steps {
                sh 'docker build -f Dockerfile.app -t git-task-app:latest .'
            }
        }

        stage('Run Tests') {
            steps {
                sh 'docker run --rm git-task-app:latest'
            }
        }

        stage('Push Images') {
            steps {
                sh '''
                docker tag git-task-app:latest ${DOCKERHUB_CREDENTIALS_USR}/git-task-app:latest
                docker push ${DOCKERHUB_CREDENTIALS_USR}/git-task-app:latest
                
                docker build -f Dockerfile.web -t ${DOCKERHUB_CREDENTIALS_USR}/git-task-web:latest .
                docker push ${DOCKERHUB_CREDENTIALS_USR}/git-task-web:latest
                '''
            }
        }

        stage('Helm Package') {
            steps {
                sh '''
                helm version
                helm package helm/test-repo-chart
                '''
            }
        }

        stage('Create Tag') {
            steps {
                script {
                    def TAG = "v${new Date().format('yyyyMMddHHmmss')}"
                    env.TAG = TAG
                    
                    sh """
                    git config user.name "jenkins"
                    git config user.email "jenkins@example.com"
                    git tag ${TAG}
                    git push https://${GITHUB_TOKEN}@github.com/MikeV182/git-task.git ${TAG}
                    """
                }
            }
        }

        stage('Deploy to Kubernetes') {
            steps {
                sh '''
                helm upgrade --install my-release helm/test-repo-chart \
                    --set app.image.repository=${DOCKERHUB_CREDENTIALS_USR}/git-task-app \
                    --set web.image.repository=${DOCKERHUB_CREDENTIALS_USR}/git-task-web \
                    --kubeconfig $KUBECONFIG
                '''
            }
        }

        // Публикация Helm-чарта в GitHub Pages
        //stage('Publish Helm Chart') {
        //    when {
        //        expression { env.TAG != null }
        //    }
        //    steps {
        //        sh '''
        //        git clone https://${GITHUB_TOKEN}@github.com/MikeV182/helm-charts.git
        //        mv test-repo-chart-*.tgz helm-charts/
        //        cd helm-charts
        //        helm repo index .
        //        git add .
        //        git commit -m "Add new chart version ${TAG}"
        //        git push https://${GITHUB_TOKEN}@github.com/MikeV182/helm-charts.git
        //        '''
        //    }
        //}
    }

    post {
        always {
            sh 'docker logout'
            cleanWs()
        }
        success {
            slackSend(color: "good", message: "Pipeline SUCCESS: ${env.JOB_NAME} ${env.BUILD_NUMBER}")
        }
        failure {
            slackSend(color: "danger", message: "Pipeline FAILED: ${env.JOB_NAME} ${env.BUILD_NUMBER}")
        }
    }
}
