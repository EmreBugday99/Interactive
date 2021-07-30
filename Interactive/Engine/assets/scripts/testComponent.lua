
function BeginPlay()
    selfEntity = GetEntity()
    sprite = CreateSprite(selfEntity)
    hashedTypeId = GetTypeHash(sprite)
    print("Lua:", hashedTypeId)
end

function Update(deltaTime)
end