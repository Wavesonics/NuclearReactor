extends Control


# Declare member variables here.
onready var audio := $GeigerCounter as AudioStreamPlayer


# Called when the node enters the scene tree for the first time.
func _ready():
	pass


func _on_Button_pressed():
	test_audio()


func test_audio():
	var playback := audio.get_stream_playback()
	
	fill_buffer(playback)
	
	audio.play()


func fill_buffer(playback):
	var to_fill = playback.get_frames_available()
	while (to_fill > 0):
		playback.push_frame( Vector2(1.0,1.0)) 
		to_fill-=1;
