package com.example.seray.mantaryetistirme7mart;


import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
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


public class OzelKontrolActivity extends AppCompatActivity {


    //TextView txtArduino;
    Handler h;

    final int ALINAN_MESAJ = 1;
    private BluetoothAdapter bluetoothAdapter = null;
    private BluetoothSocket bluetoothSocket = null;
    private StringBuilder stringBuilder = new StringBuilder();

    private ConnectedThread mConnectedThread;

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

   // private static String address = "20:16:05:19:23:97";
   private static String address = "20:17:02:15:04:69";
    ToggleButton buton1, buton2, buton3, buton4, buton5;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ozel_kontrol);

        ToggleButton buton1 = (ToggleButton) findViewById(R.id.id_toggleButton_isitici);
        ToggleButton buton2 = (ToggleButton) findViewById(R.id.id_toggleButton_sogutucu);
        ToggleButton buton3 = (ToggleButton) findViewById(R.id.id_toggleButton_sulama);
        ToggleButton buton4 = (ToggleButton) findViewById(R.id.id_toggleButton_havalandirma);
        ToggleButton buton5 = (ToggleButton) findViewById(R.id.id_toggleButton_nemlendirme);

      //  txtArduino = (TextView) findViewById(R.id.txtArduino);        // for display the received data from the Arduino

     /*   h = new Handler() {
            public void handleMessage(android.os.Message mesaj) {
                switch (mesaj.what) {
                    case ALINAN_MESAJ:
                        byte[] readBuf = (byte[]) mesaj.obj;
                        String kelime = new String(readBuf, 0, mesaj.arg1);
                        stringBuilder.append(kelime);
                        int satirSonu = stringBuilder.indexOf("\r\n");
                        if (satirSonu > 0) {
                            String mesajiAl = stringBuilder.substring(0, satirSonu);
                            stringBuilder.delete(0, stringBuilder.length());
                            txtArduino.setText("Arduino'dan gelen mesaj: " + mesajiAl);

                        }
                        break;
                }
            }

            ;
        };*/

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        bluetoothKontroluYap();

        buton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                boolean aktif = ((ToggleButton) v).isChecked();

                if (aktif) {
                    mConnectedThread.yolla("0");
                    Toast.makeText(getBaseContext(), "Isıtıcı Açıldı", Toast.LENGTH_SHORT).show();
                    //mConnectedThread.run();


                } else {
                    mConnectedThread.yolla("1");
                    Toast.makeText(getBaseContext(), "Isıtıcı Kapandı", Toast.LENGTH_SHORT).show();
                    //mConnectedThread.run();


                }


            }
        });

        buton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                boolean aktif = ((ToggleButton) v).isChecked();

                if (aktif) {
                    mConnectedThread.yolla("2");
                    Toast.makeText(getBaseContext(), "Soğutucu Açıldı", Toast.LENGTH_SHORT).show();



                } else {
                    mConnectedThread.yolla("3");
                    Toast.makeText(getBaseContext(), "Soğutucu Kapandı", Toast.LENGTH_SHORT).show();


                }


            }
        });
        buton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                boolean aktif = ((ToggleButton) v).isChecked();

                if (aktif) {
                    mConnectedThread.yolla("4");
                    Toast.makeText(getBaseContext(), "Sulama Açıldı", Toast.LENGTH_SHORT).show();


                } else {
                    mConnectedThread.yolla("5");
                    Toast.makeText(getBaseContext(), "Sulama Kapandı", Toast.LENGTH_SHORT).show();

                }
            }
        });
        buton4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                boolean aktif = ((ToggleButton) v).isChecked();

                if (aktif) {
                    mConnectedThread.yolla("6");
                    Toast.makeText(getBaseContext(), "Havalandırma Açıldı", Toast.LENGTH_SHORT).show();

                } else {
                    mConnectedThread.yolla("7");
                    Toast.makeText(getBaseContext(), "Havalandırma Kapandı", Toast.LENGTH_SHORT).show();

                }

            }
        });
        buton5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                boolean aktif = ((ToggleButton) v).isChecked();

                if (aktif) {
                    mConnectedThread.yolla("8");
                    Toast.makeText(getBaseContext(), "Nemlendirme Açıldı", Toast.LENGTH_SHORT).show();


                } else {
                    mConnectedThread.yolla("9");
                    Toast.makeText(getBaseContext(), "Nemlendirme Kapandı", Toast.LENGTH_SHORT).show();

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


        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(address);


        try {
            bluetoothSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            cikisYap("Fatal Error", "In onResume() and socket create failed: " + e.getMessage() + ".");
        }

        bluetoothAdapter.cancelDiscovery();


        try {
            bluetoothSocket.connect();
        } catch (IOException e) {
            try {
                bluetoothSocket.close();
            } catch (IOException e2) {
                cikisYap("Fatal Error", "In onResume() and unable to close socket during connection failure" + e2.getMessage() + ".");
            }
        }


        mConnectedThread = new ConnectedThread(bluetoothSocket);
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

        if (bluetoothAdapter == null) {
            cikisYap("HATA", "Bluetooth desteklenmiyor");
        } else {
            if (bluetoothAdapter.isEnabled()) {
            } else {
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