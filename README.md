# fun-game

A fun game which isn't that fun.

Do not waste your life on it.(it's buggy and unfinished)

## Build

**Server(Linux)**

Clone this repo and

```
cd ./server
make
./s
```

the server(and the client) program uses UDP port 9998, make sure it's open to public on your server.

**Client(Windows)**

1. Download the [release](https://github.com/goverclock/fun-game/releases).

2. Edit `servadr` file, the first line as server ip, do not modify the second line.

e.g. run server on localhost:
```
127.0.0.1
9998
```

**Client(Linux)**

1. Install Qt and build it with fun-game/CMakeLists.txt.

2. Edit `servadr` file like on Windows.

## How to play

![](./usage.gif)

- use /s to start a game
- use /e to end a game
- in game, use A and D to change your angle
- in game, hold Shift and release to launch

You can modify the map by editing `bgobj` file of client. Make sure all clients have the same `bgobj` file.

- each line has two numbers, x, y of a point
- connect these points in order you get a polygon, the polygon is added to the map
- you can add multiple polygons, make sure each polygon's points are seperated by an empty line
- end the file with double empty lines

e.g. the `bgobj` file of the GIF.

```
0 200
0 420
600 420
600 200
500 100
400 200
300 100
200 200
100 100


```

## BUGs

Everything is buggy, not gonna fix them.

- I used UDP, which is totally wrong, once a datagram is lost the whole system gets stuck
- In some situation the program would delete an invalid pointer, and your client crashes
