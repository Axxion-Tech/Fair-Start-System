import asyncio
from bleak import BleakClient

address = "10:08:2C:1F:3B:89"
MODEL_NBR_UUID = 0xFFE1

async def main(address):
    client = BleakClient(address)
    try:
        services = client.services
        print(client)
        print(services)
        await client.connect()
        response = await client.write_gatt_char(MODEL_NBR_UUID, bytearray("4", "utf-8"), True)
        print(response)
    except Exception as e:
        print(e)
    finally:
        await client.disconnect()

asyncio.run(main(address))

# import asyncio
# from bleak import BleakClient

# address = "10:08:2C:1F:3B:89"
# MODEL_NBR_UUID = "00002a24-0000-1000-8000-00805f9b34fb"

# async def main(address):
#     async with BleakClient(address) as client:
#         await client.connect()
#         connected = await client.is_connected()
#         print(connected)
#         # model_number = await client.write_gatt_char(MODEL_NBR_UUID, "4", True)
#         # print("Model Number: {0}".format("".join(map(chr, model_number))))

# asyncio.run(main(address))