# RuStore InApp — Defold Extension

Defold extension for in-app purchases via [RuStore Pay SDK](https://www.rustore.ru/help/sdk/pay/defold/10-1-0).

## Installation

Open `game.project` and add to **Dependencies** (Project → Dependencies):

```
https://github.com/osov/defold-rustore-inapp/archive/main.zip
```

## Setup

### game.project

Add the following section to your `game.project`:

```ini
[rustore]
console_app_id = YOUR_APP_ID
deeplink_scheme = your.package.name.rustore.scheme
```

- `console_app_id` — ID приложения из [RuStore Console](https://console.rustore.ru/)
- `deeplink_scheme` — deeplink-схема для возврата из оплаты (ASCII, RFC-3986)

Deeplink activity и meta-data подключаются автоматически через манифест расширения.

### AndroidManifest.xml

В вашем главном манифесте необходимо:

1. Добавить `tools:replace="android:label"` в `<application>` (требование RuStore SDK)
2. **Убрать LAUNCHER intent-filter у `DefoldActivity`** — точкой входа станет `RuStoreIntentFilterActivity` из расширения (обрабатывает возврат из оплаты и запускает `DefoldActivity`)

```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    ...>

    <application
        ...
        tools:replace="android:label"
        ...>

        <!-- Убрать intent-filter с LAUNCHER у DefoldActivity -->
        <activity android:name="com.dynamo.android.DefoldActivity"
            ...
            android:exported="true"
            android:launchMode="singleTask">
            <meta-data android:name="android.app.lib_name" android:value="{{exe-name}}" />
            <!-- НЕТ intent-filter с MAIN/LAUNCHER здесь -->
        </activity>

    </application>
</manifest>
```

## Lua API

### rustorecore

Модуль ядра — подписка на события, утилиты.

```lua
-- Подписка на канал событий
rustorecore.connect(channel, callback)

-- Утилиты
rustorecore.show_toast(message)
rustorecore.is_rustore_installed()          -- returns bool
rustorecore.open_rustore()
rustorecore.open_rustore_authorization()
rustorecore.open_rustore_download_instruction()

-- Clipboard
rustorecore.copy_to_clipboard(text)
rustorecore.get_from_clipboard()            -- returns string

-- SharedPreferences
rustorecore.get_string_shared_preferences(storage, key, default)
rustorecore.set_string_shared_preferences(storage, key, value)
rustorecore.get_int_shared_preferences(storage, key, default)
rustorecore.set_int_shared_preferences(storage, key, value)

-- Resources
rustorecore.get_string_resources(name)      -- returns string

-- Logging
rustorecore.log_verbose(tag, message)
rustorecore.log_debug(tag, message)
rustorecore.log_info(tag, message)
rustorecore.log_warning(tag, message)
rustorecore.log_error(tag, message)
```

### rustorepay

Модуль оплаты — покупки, продукты, статусы.

```lua
-- Проверка доступности платежей
rustorepay.get_purchase_availability()

-- Получение списка продуктов
rustorepay.get_products({"product_id_1", "product_id_2"})

-- Покупка (one-step)
rustorepay.purchase(json_params, "ONE_STEP")
-- Покупка (two-step)
rustorepay.purchase_two_step(json_params)

-- Подтверждение / отмена two-step покупки
rustorepay.confirm_two_step_purchase(purchase_id, developer_payload)
rustorepay.cancel_two_step_purchase(purchase_id)

-- Получение покупок
rustorepay.get_purchases()                  -- все покупки
rustorepay.get_purchases({productType = "...", purchaseStatus = "..."})
rustorepay.get_purchase(purchase_id)        -- одна покупка

-- Статус авторизации
rustorepay.get_user_authorization_status()
```

## Events

Все ответы приходят через `rustorecore.connect(channel, callback)`:

| Channel | Callback args |
|---------|--------------|
| `rustore_pay_on_get_purchase_availability_success` | `self, channel, json` |
| `rustore_pay_on_get_purchase_availability_failure` | `self, channel, error` |
| `rustore_pay_on_get_products_success` | `self, channel, json` |
| `rustore_pay_on_get_products_failure` | `self, channel, error` |
| `rustore_pay_on_purchase_success` | `self, channel, json` |
| `rustore_pay_on_purchase_failure` | `self, channel, error` |
| `rustore_pay_on_get_purchases_success` | `self, channel, json` |
| `rustore_pay_on_get_purchases_failure` | `self, channel, error` |
| `rustore_pay_on_get_purchase_success` | `self, channel, json` |
| `rustore_pay_on_get_purchase_failure` | `self, channel, error` |
| `rustore_pay_on_confirm_two_step_purchase_success` | `self, channel, value` |
| `rustore_pay_on_confirm_two_step_purchase_failure` | `self, channel, error, id` |
| `rustore_pay_on_cancel_two_step_purchase_success` | `self, channel, value` |
| `rustore_pay_on_cancel_two_step_purchase_failure` | `self, channel, error, id` |

## Example

```lua
function init(self)
    if not rustorepay then
        print("rustorepay not available — build for Android")
        return
    end

    rustorecore.connect("rustore_pay_on_get_products_success", function(self, channel, value)
        local products = json.decode(value)
        for i, p in ipairs(products) do
            print(p.productId, p.title, p.amountLabel)
        end
    end)

    rustorecore.connect("rustore_pay_on_purchase_success", function(self, channel, value)
        local data = json.decode(value)
        print("Purchased!", data.purchaseId, data.productId)
    end)

    rustorepay.get_products({"product_100", "product_500"})
end
```

## Platform

Android only (minimum SDK 24). On other platforms `rustorecore` and `rustorepay` modules are empty stubs.

## Links

- [RuStore Pay SDK Defold Docs](https://www.rustore.ru/help/sdk/pay/defold/10-1-0)
- [Official Example](https://gitflic.ru/project/rustore/rustore-defold-pay)
