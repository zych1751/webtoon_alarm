#-*- coding: utf-8 -*-
import requests
from bs4 import BeautifulSoup
import json
import datetime
import time
import tornado.websocket
from tornado.ioloop import IOLoop
from tornado import gen

CONFIG_FILE='./webtoon_info.json'
CONFIG={}

def readConfig(filename):
    try:
        f = open(filename, 'r')
        js = json.loads(f.read())
        f.close()
    except:
        js = {}
        print("cannot read")
    return js

@gen.coroutine
def crawl():
    global CONFIG_FILE
    global CONFIG
    change = False

    CONFIG = readConfig(CONFIG_FILE)

    if ('naver' in CONFIG) == False:
        CONFIG['naver'] = {}

# naver
    default = 'http://comic.naver.com/webtoon/weekdayList.nhn?week='
    days = ['mon', 'tue', 'wed', 'thu', 'fri', 'sat', 'sun']

    cur_time = str(datetime.datetime.now())
    
    for day in days:
        if (day in CONFIG['naver']) == False:
            CONFIG['naver'][day] = {}

        url = default+day
        soup = BeautifulSoup(requests.get(url).text, 'lxml')

        for link in soup.select('.img_list > li > dl > dt > a'):
            title = link.attrs['title']
            if (title in CONFIG['naver'][day]) == False:
                CONFIG['naver'][day][title] = {}

            href = 'http://comic.naver.com' + link.attrs['href']
            soup2 = BeautifulSoup(requests.get(href).text, 'lxml')
            recent = soup2.select('.title > a')[0]
            recent_href = recent.attrs['href']
            recent_title = recent.text

            if ('recent_title' in CONFIG['naver'][day][title]) == False or CONFIG['naver'][day][title]['recent_title'] != recent_title:
                CONFIG['naver'][day][title]['recent_title'] = recent_title
                CONFIG['naver'][day][title]['recent_href'] = recent_href
                CONFIG['naver'][day][title]['recent_time'] = cur_time
                change = True

        yield gen.Task(
            IOLoop.current().add_timeout,
            datetime.timedelta(milliseconds=500))

    with open(CONFIG_FILE, 'w') as outfile:
        json.dump(CONFIG, outfile, ensure_ascii=False, indent="\t")
    print("crawling end")

    if change:
        send_to_all_clients(json.dumps(CONFIG, ensure_ascii=False, indent="\t"))


############## WebSocket
clients = []

def send_to_all_clients(msg):
    for client in clients:
        client.write_message(msg)

class WSHandler(tornado.websocket.WebSocketHandler):
    def open(self):
        clients.append(self)
        self.write_message(readConfig(CONFIG_FILE))
        print(len(clients))

    def on_close(self):
        clients.remove(self)
        print(len(clients))

    def on_message(self, message):
        return

############## Main

@gen.coroutine
def loop():
    while True:
        print("crawling...")
        prev = time.time()
        crawl()
        
        wait_time = 180 - (time.time() - prev)
        if wait_time < 0:
            wait_time = 0

        yield gen.Task(
            IOLoop.current().add_timeout,
            datetime.timedelta(seconds=wait_time))

def main():
    application = tornado.web.Application([
        (r'/', WSHandler),
    ])
    application.listen(8888)

    loop()
    print("server start")
    IOLoop.current().start()

main()
