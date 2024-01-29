extends RigidBody2D

@onready var _animated_sprite = $AnimatedSprite2D
@export var speed = 5000
@export var max_velocity = Vector2(1000, 1000)

# Called when the node enters the scene tree for the first time.
func _ready():
	_animated_sprite.play("player_idle_animation")

func swap_sprite_direction(input_direction):
	if (input_direction as Vector2).x > 0:
		_animated_sprite.set_flip_h(false)
	elif (input_direction as Vector2).x < 0:
		_animated_sprite.set_flip_h(true)

# Retrieves the input and updates the target velocity
func get_input():
	var input_direction = Input.get_vector("left", "right", "up", "down")
	swap_sprite_direction(input_direction)
	apply_force(input_direction * speed)
	linear_velocity = clamp(linear_velocity, max_velocity * -1, max_velocity)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta):
	get_input()
