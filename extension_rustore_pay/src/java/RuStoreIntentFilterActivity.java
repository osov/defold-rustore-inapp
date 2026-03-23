package ru.rustore.defold.pay;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class RuStoreIntentFilterActivity extends Activity {

    private final String defoldActivityClassName = "com.dynamo.android.DefoldActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (savedInstanceState == null) {
            RuStorePay.INSTANCE.proceedIntent(getIntent());
        }

        startGameActivity(defoldActivityClassName);
        finish();
    }

    @Override
    public void onNewIntent(Intent intent) {
        super.onNewIntent(intent);

        RuStorePay.INSTANCE.proceedIntent(intent);
    }

    private void startGameActivity(String gameActivityClassName) {
        Class<?> gameActivityClass = getActivityClass(gameActivityClassName);
        if (gameActivityClass != null) {
            Intent intent = new Intent(this, gameActivityClass);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
            startActivity(intent);
        }
    }

    private Class<?> getActivityClass(String activityClassName) {
        try {
            return Class.forName(activityClassName);
        } catch(ClassNotFoundException ex) {
            return null;
        }
    }
}
