

// // xcopy /�ɼ� .������ ������ ���ִ� ���      .���ϵ��� ������ ��� 

xcopy /y/s	.\Core\Public\*.*														.\Reference\Headers\

xcopy /y/s	.\Core\Bin\debug\*.lib											.\Reference\Librarys\
xcopy /y/s	.\Core\Bin\release\*.lib											.\Reference\Librarys\

xcopy /y/s	.\Core\Bin\*.dll															.\Server\Bin\
xcopy /y/s	.\Core\Bin\*.dll															.\TestClient\Bin\



xcopy /y/s	.\Core\ThirdPartyLib\*.Lib										.\Reference\Librarys\
xcopy /y/s	.\ProtocolBuffer\ServerProtocol\*.*						.\Reference\Headers\
xcopy /y/s	.\ProtocolBuffer\Public\*.*										.\Reference\Headers\
xcopy /y/s	.\ProtocolBuffer\Bin\*.lib											.\Reference\Librarys\
xcopy /y/s	.\ProtocolBuffer\ThirdPartyLib\*.lib						.\Reference\Librarys\


xcopy /y/s	.\ProtocolBuffer\ServerProtocol\*.*						.\(OutPut)\Headers\
xcopy /y/s	.\ProtocolBuffer\Public\*.*										.\(OutPut)\Headers\
xcopy /y/s	.\ProtocolBuffer\Bin\*.lib											.\(OutPut)\Librarys\
xcopy /y/s	.\ProtocolBuffer\ThirdPartyLib\*.lib						.\(OutPut)\Librarys\




