import requests

# Your API key
api_key = 'yourapikey'

# Endpoint URL
url = 'https://order.gelatoapis.com/v4/orders'

# Order data
order_data = {
    "orderType": "order",
    "orderReferenceId": "your_order_id",
    "customerReferenceId": "your_customer_id",
    "currency": "USD",
    "items": [
        {
            "itemReferenceId": "item_id_1",
            "productUid": "photobooks-softcover_pf_140x140-mm-5_5x5_5-inch_pt_170-gsm-65lb-coated-silk_cl_4-4_ccl_4-4_bt_glued-left_ct_matt-lamination_prt_1-0_cpt_250-gsm-100-lb-cover-coated-silk_ver",
            "pageCount": 30,
            "files": [
                {
                    "type": "default",
                    "url": "link to pdf file"
                }
            ],
            "quantity": 1
        }
    ],
    "shipmentMethodUid": "express",
    "shippingAddress": {
        "companyName": "Your Company",
        "firstName": "First",
        "lastName": "Last",
        "addressLine1": "123 Main St",
        "addressLine2": "",
        "state": "CA",
        "city": "Los Angeles",
        "postCode": "90001",
        "country": "US",
        "email": "youremail@gmail.com",
        "phone": "1234567890"
    }
}

# Headers
headers = {
    'Content-Type': 'application/json',
    'X-API-KEY': api_key
}

# Send the POST request
response = requests.post(url, json=order_data, headers=headers)

# Check the response
if response.status_code == 200:
    print('Order placed successfully.')
else:
    print(f'Failed to place order. Status code: {response.status_code}')
    print('Response:', response.json())
