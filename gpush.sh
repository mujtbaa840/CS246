#!/bin/bash

# Get current date and time
TIMESTAMP=$(date "+%Y-%m-%d %H:%M:%S")

# Use provided commit message or default one
if [ -z "$1" ]; then
    COMMIT_MESSAGE="Repository Update - $TIMESTAMP"
else
    COMMIT_MESSAGE="$1 - $TIMESTAMP"
fi

git pull
git add .
git commit -m "$COMMIT_MESSAGE"
git push

# ./gpush.sh
# ./gpush.sh "Commit message"