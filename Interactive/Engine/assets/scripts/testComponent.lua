
function BeginPlay()
	print("Hello from BeginPlay!")
	EnableKeyboardCallback()
end

function Update(deltaTime)
	print("Hello from Update! " , deltaTime)
end

function KeyboardCallback()
end