#pragma once
/// <summary>
/// ecs components
/// </summary>

struct Position {
    int x;
    int y;
};

struct Velocity {
    int dx;
    int dy;
};

struct Texture {
    int index;
};

struct Player {
    int id;
};