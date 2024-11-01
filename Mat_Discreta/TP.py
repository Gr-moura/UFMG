import tkinter as tk
import turtle

size = 10

def um(t, ordem, atual, ang):
    if ordem == 0:
        for command in regra:
            if command == 'F':
                t.forward(size)
            elif command == '-':
                t.left(ang)
            elif command == '+':
                t.right(ang)
        return

    while atual < len(regra):
        if regra[atual] == 'F':
            um(t, ordem - 1, 0, ang)
            atual += 1
            continue

        if regra[atual] == '-':
            t.left(ang)
        elif regra[atual] == '+':
            t.right(ang)
        atual += 1

def dois(t, ordem, atual, pai):
    if ordem == 0:
        for command in hilbert[pai]:
            if command == 'F':
                t.forward(size)
            elif command == '-':
                t.left(ang)
            elif command == '+':
                t.right(ang)
        return

    while atual < len(hilbert[pai]):
        if hilbert[pai][atual] == 'X':
            dois(t, ordem - 1, 0, 0)
        elif hilbert[pai][atual] == 'Y':
            dois(t, ordem - 1, 0, 1)
        else:
            if hilbert[pai][atual] == 'F':
                t.forward(size)
            elif hilbert[pai][atual] == '-':
                t.left(ang)
            elif hilbert[pai][atual] == '+':
                t.right(ang)
        atual += 1

# Set up the Tkinter window and the Turtle screen
root = tk.Tk()
root.title("Recursive Sierpinski Triangle")

# Create a canvas and associate it with the Turtle
canvas = tk.Canvas(root, width=600, height=600)
canvas.pack()

screen = turtle.TurtleScreen(canvas)
screen.bgcolor("white")

# Create the turtle
t = turtle.RawTurtle(screen)

def UM(a):
    if (a == 1):
        t.speed(0)  # Fastest speed
        t.penup()
        t.goto(0, 0)  # Start in the middle of the left side
        t.setheading(0)  # Point the turtle to the right (0 degrees)
        t.pendown()
        t.hideturtle()
        for i in axioma:
            if i == 'F':
                um(t, ordem - 1, 0, ang)
                continue
            if i == '-':
                t.left(ang)
            elif i == '+':
                t.right(ang)

    if (a == 2):
        t.speed(0)  # Fastest speed
        t.penup()
        t.goto(-300, -300)  # Start in the middle of the left side
        t.setheading(0)  # Point the turtle to the right (0 degrees)
        t.pendown()
        t.hideturtle()
        for command in axioma:
            if command == 'F':
                t.forward(size)
                continue
            if command == '-':
                t.left(ang)
            elif command == '+':
                t.right(ang)
            elif command == 'X':
                dois(t, ordem - 1, 0, 0)
            elif command == 'Y':
                dois(t, ordem - 1, 0, 1)

axioma = "X"
ang = 90
ordem = 6
regra = "F+F-F-FFF+F+F-F"
hilbert = ["-YF+XFX+FY-", "+XF-YFY-FX+"]
UM(2)
# Run the Tkinter main loop
root.mainloop()
