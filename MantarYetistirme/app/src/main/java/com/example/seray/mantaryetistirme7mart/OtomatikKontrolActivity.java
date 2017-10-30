package com.example.seray.mantaryetistirme7mart;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.UUID;


public class OtomatikKontrolActivity extends AppCompatActivity {

   // TextView txtArduino;
    Handler h;

   // final int ALINAN_MESAJ = 1;//Handler dan gelen icin
    private BluetoothAdapter bluetoothAdaptor = null;
    private BluetoothSocket bluetoothSocket = null;
    private StringBuilder stringBuilder = new StringBuilder();

    private OtomatikKontrolActivity.ConnectedThread mConnectedThread;

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

   // private static String adres = "20:16:05:19:23:97";
    private static String adres = "20:17:02:15:04:69";

    ToggleButton buton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_otomatik_kontrol);

        buton = (ToggleButton) findViewById(R.id.id_toggleButton_oto);

      //  txtArduino = (TextView) findViewById(R.id.txtArduino);//arduinodan gelen veriyi ekrana basmak icin

        /*
        h = new Handler() {
            public void handleMessage(android.os.Message mesaj) {
                switch (mesaj.what) {
                    case ALINAN_MESAJ:
                        byte[] readBuf = (byte[]) mesaj.obj;
                        String kelime = new String(readBuf, 0, mesaj.arg1);//bayt array
                        stringBuilder.append(kelime);//append etme
                        int satirSonu = stringBuilder.indexOf("\r\n");//satir sonu
                        if (satirSonu > 0) { //satir sonu ise
                            String mesajiAl = stringBuilder.substring(0, satirSonu);//mesaji al
                            stringBuilder.delete(0, stringBuilder.length());    //temizle
                            txtArduino.setText("Arduino'dan gelen mesaj: " + mesajiAl);
                        }
                        break;
                }
            }

            ;
        };*/

        bluetoothAdaptor = BluetoothAdapter.getDefaultAdapter();
        bluetoothKontroluYap();

        buton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                boolean aktif = ((ToggleButton) v).isChecked();

                if (aktif) {
                    // Aktifte yapılacaklar
                    mConnectedThread.yolla("S");
                    Toast.makeText(getBaseContext(), "Otomatik Sistem Devrede", Toast.LENGTH_SHORT).show();


                } else {
                    // Pasifte yapılacaklar
                    mConnectedThread.yolla("D");
                    Toast.makeText(getBaseContext(), "Otomatik Sistem Devre Dışı", Toast.LENGTH_SHORT).show();


                }
            }
        });


    }


    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        if (Build.VERSION.SDK_INT >= 10) {
            try {
                final Method m = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[]{UUID.class});
                return (BluetoothSocket) m.invoke(device, MY_UUID);
            } catch (Exception e) {
            }
        }
        return device.createRfcommSocketToServiceRecord(MY_UUID);
    }

    @Override
    public void onResume() {
        super.onResume();


        BluetoothDevice device = bluetoothAdaptor.getRemoteDevice(adres);

        try {
            bluetoothSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            cikisYap("Fatal Error", "In onResume() and socket create failed: " + e.getMessage() + ".");
        }


        bluetoothAdaptor.cancelDiscovery();

        try {
            bluetoothSocket.connect();
        } catch (IOException e) {
            try {
                bluetoothSocket.close();
            } catch (IOException e2) {
                cikisYap("Fatal Error", "In onResume() and unable to close socket during connection failure" + e2.getMessage() + ".");
            }
        }


        mConnectedThread = new OtomatikKontrolActivity.ConnectedThread(bluetoothSocket);
        mConnectedThread.start();
    }

    @Override
    public void onPause() {
        super.onPause();

        try {
            bluetoothSocket.close();
        } catch (IOException e2) {
            cikisYap("Fatal Error", "In onPause() and failed to close socket." + e2.getMessage() + ".");
        }
    }

    private void bluetoothKontroluYap() {

        if (bluetoothAdaptor == null) {
            cikisYap("HATA", "Bluetooth desteklenmiyor");
        } else {
            if (bluetoothAdaptor.isEnabled()) {
            } else {//bluetooth acma islemi
                Intent bluetoothAcma = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(bluetoothAcma, 1);
            }
        }
    }

    private void cikisYap(String title, String message) {
        Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
        finish();
    }

    private class ConnectedThread extends Thread {
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }
/*
        public void run() {
            byte[] buffer = new byte[256];
            int bytes;
            while (true) {
                try {
                    bytes = mmInStream.read(buffer);
                    h.obtainMessage(ALINAN_MESAJ, bytes, -1, buffer).sendToTarget();
                } catch (IOException e) {
                    break;
                }
            }
        }*/

        public void yolla(String message) {
            byte[] msgBuffer = message.getBytes();
            try {
                mmOutStream.write(msgBuffer);
            } catch (IOException e) {
            }
        }
    }
}