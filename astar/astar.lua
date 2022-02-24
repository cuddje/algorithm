--0: 可通过 1:障碍物
local cfg = {
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, --1
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, --2
  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, --3
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, --4
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, --5
  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, --6
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, --7
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, --8
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, --9
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, --10
}
local width, height = 10,10

local function gid(pos)
  return pos.y * width + pos.x
end
local function position(x, y)
  return {x=x, y=y}
end

local function new_node(pos)
  local t = {}
  t.pos = pos
  t.parent = nil
  t.G = 0 --当前的消耗
  t.H = 0 --预估的消耗
  t.F = 0
  t.id = gid(pos)
  return t
end 

local function sort(a, b)
  return a.F < b.F
end

local function find_from_open_list(list, id)
  for _,v in pairs(list) do
    if v.id == id then
      return v
    end
  end
end

local function position_equal(p1, p2)
  return p1.x == p2.x and p1.y == p2.y
end
local function position_valid(x, y)
  return x<=width and x>=1 and y<= height and y>= 1 and cfg[x][y] == 0
end

local start = new_node(position(1, 5))
local goal  = new_node(position(10, 5))
local close_list = {}
local open_list = {[1] = start}
local find = nil


while (#open_list ~= 0) do
  table.sort(open_list, sort)
  local current = open_list[1]--取F最小的作为当前节点
  table.remove(open_list, 1)  --从open_list中移除
  close_list[current.id] = current--添加到关闭列表
  if current.id == goal.id then
    find = current
    break
  end

  --只取周围4个方向
  for _,dir in ipairs({ {1,0}, {-1,0}, {0,1}, {0,-1} }) do
    local x,y = current.pos.x + dir[1], current.pos.y + dir[2]
    local id = gid(position(x, y))
    if position_valid(x, y) and close_list[id] == nil then--有效节点而且不在关闭列表中
      local next_node = find_from_open_list(open_list, id)
      if next_node ~= nil then  --已经在开放列表中
        --检查经过这个节点到达 是否F值会更低
        if current.G + 10 < next_node.G then
          next_node.parent = current
          next_node.G = current.G + 10
          next_node.F = next_node.G + next_node.H
        end
      else                      --加入开放列表
        next_node = new_node(position(x, y))
        next_node.parent = current
        next_node.G = current.G + 10
        next_node.F = next_node.G + next_node.H
        table.insert(open_list, next_node)
      end
    end
  end
end

local path = {}
local tmp = {}
local node = find
while node ~= nil do
  table.insert(tmp, node)
  node = node.parent
end
for i=#tmp,1,-1 do
  table.insert(path, tmp[i])
end

local path_map = {}
for _,v in ipairs(path) do
  local id = gid(v.pos)
  path_map[id] = 6
end
local function get_value(x, y)
  local id = gid(position(x, y))
  return path_map[id] or cfg[x][y]
end

for y,line in ipairs(cfg) do
  local value = ''
  for x,_ in ipairs(line) do
    value = value .. get_value(x, y) .. '  '
  end
  print('line'..y..': ' .. value)
end