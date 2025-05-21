#!/bin/sh

LOG_FILE="/usr/share/nginx/html/index.html"

# Функция обновления логов
update_logs() {
    POD=$(kubectl get pods -l app=test-repo-app -o jsonpath='{.items[0].metadata.name}' 2>/dev/null)

    echo "<html><head><meta http-equiv=\"refresh\" content=\"5\"><title>Logs</title></head><body><pre>" > "$LOG_FILE"

    if [ -n "$POD" ]; then
        kubectl logs "$POD" >> "$LOG_FILE" 2>&1
    else
        echo "No pod found with label app=test-repo-app" >> "$LOG_FILE"
    fi

    echo "</pre></body></html>" >> "$LOG_FILE"
}

# Запуск nginx
nginx

# Периодическое обновление логов
while true; do
    update_logs
    sleep 5
done