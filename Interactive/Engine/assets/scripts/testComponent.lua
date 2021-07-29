
entity = GetEntity();
entity2 = CreateEntity("asdas")

sprite = CreateSprite(entity)

function BeginPlay()
	print("Hello from BeginPlay!")
end

function Update(deltaTime)
	if IsKeyPressed("W") == true then
		print(sprite)
	end
	
	if IsKeyPressed("F") == true then
		Destroy(entity)
		Destroy(entity2)
	end
end