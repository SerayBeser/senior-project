package com.example.seray.mantaryetistirme7mart;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.Toast;

public class AyarlarActivity extends AppCompatActivity {
    Button buton6,buton7;

    Switch bildirim,bluetooth;
    
    final BluetoothAdapter adapter=BluetoothAdapter.getDefaultAdapter();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ayarlar);



        buton6=(Button)findViewById(R.id.id_button_urunbilgisi);


        buton6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(AyarlarActivity.this, MantarDurumuActivity.class);
                startActivity(intent);
            }
        });

        buton7=(Button)findViewById(R.id.id_button_kontrol);


        buton7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(AyarlarActivity.this, KontrolActivity.class);
                startActivity(intent);
            }
        });

        bildirim=(Switch)findViewById(R.id.id_switch_bildirim);

        bildirim.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {

                if(isChecked){

                    Intent intent = new Intent();
                    PendingIntent i = PendingIntent.getActivity(AyarlarActivity.this, 0, intent, 0);

                    Notification bildirim = new Notification.Builder(AyarlarActivity.this)
                            .setTicker("SHROO")
                            .setContentTitle("SHROO")
                            .setContentText("SHROO Bildirimleri Acildi.")
                            .setSmallIcon(R.drawable.mantarbilgi).setContentIntent(i)
                            .getNotification();
                    bildirim.flags = Notification.FLAG_SHOW_LIGHTS;

                    NotificationManager bildirimYonetici = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
                    bildirimYonetici.notify(0, bildirim);
                }else{

                    Intent intent = new Intent();
                    PendingIntent i = PendingIntent.getActivity(AyarlarActivity.this, 0, intent, 0);

                    Notification bildirim = new Notification.Builder(AyarlarActivity.this)
                            .setTicker("SHROO")
                            .setContentTitle("SHROO")
                            .setContentText("SHROO Bildirimleri Kapandi.")
                            .setSmallIcon(R.drawable.mantarbilgi).setContentIntent(i)
                            .getNotification();
                    bildirim.flags = Notification.FLAG_SHOW_LIGHTS;

                    NotificationManager bildirimYonetici = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
                    bildirimYonetici.notify(0, bildirim);
                }

            }
        });


        bluetooth=(Switch)findViewById(R.id.id_switch_bluetooth);

        bluetooth.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {

                if(isChecked){

                    if(adapter == null){
                        Toast.makeText(getApplicationContext(), "Bluetooth Aygıtı Bulunamadi.", Toast.LENGTH_LONG).show();
                    }
                    else{
                        if(!adapter.isEnabled()){
                            Intent i=new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                            startActivity(i);
                        }else{
                            adapter.disable();
                        }
                        if(adapter.isEnabled()){
                            Intent i=new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
                            startActivity(i);
                        }
                    }
                }else{

                    if(!adapter.isEnabled()){

                    }else{
                        adapter.disable();
                    }
                }

            }
        });


    }
}
