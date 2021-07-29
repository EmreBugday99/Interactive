
function BeginPlay()
	print("Hello from BeginPlay!")
end

function Update(deltaTime)
	if IsKeyPressed("W") == true then
		print("W pressed");
	end
end