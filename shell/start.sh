#!/bin/bash

name=bin/unix

function func_get_thread_cnt
{
    if [ ! -e ".pid" ]; then
        return 0
    fi
    pid=`cat .pid`
    return `ps axf -o pid | grep $pid | wc -l`
}

function func_process
{
    declare -i start=0

    func_get_thread_cnt $1
    if [ $? != 0 ]; then
        echo "$1 is running"

        if [ $2 != 0 ]; then
            echo "shut down $1 ..."
            kill -s  SIGUSR1 $pid
            
            wait_cnt=0
            for ((;;)); do
                if [ $wait_cnt == 10 ]; then
                    break
                fi
                func_get_thread_cnt $1
                if [ $? == 0 ]; then
                    break
                fi
                wait_cnt=$[wait_cnt+1]
                sleep 1
            done

            if [ $wait_cnt == 10 ]; then
                echo "shut down failed, please try again"
                return 1
            fi
        fi
    else
        echo "$1 is not running"

        start=1
    fi

    if [ $start != 0 ]; then
        if [ $3 != 0 ]; then
            ./$1 -d
            echo "$1 started"
        fi
    fi
}

function func_execute
{
    declare -i is_stop=0
    declare -i is_daemon=0

    while getopts "sd" opt_name; do
        case "$opt_name" in
            "s") is_stop=1;;
            "d") is_daemon=1;;
            "h")
                echo "\t---Args---"
                echo "\t -s = stop server"
                echo "\t -d = start server with daemon"
                echo "\t -h = print help"
                return 0;;
            "?") echo "Unknown option"; return 1;;
        esac
    done
    func_process $name $is_stop $is_daemon
}


# -- main --

if [ $0 == "./shell/start.sh" ]; then
    if [ $# -eq 0 ]; then
        func_execute -d
    else
        func_execute $@
    fi
elif [ $0 == "./shell/stop.sh" ]; then
    if [ $# -eq 0 ]; then
        func_execute -s
    else
        func_execute $@
    fi
else
    echo "please run like './shell/xxx.sh'"
fi
